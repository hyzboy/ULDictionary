#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <gumbo.h>

// Helper function to search for text in Gumbo parse tree
void searchForText(GumboNode* node, QStringList& texts) {
    if (node->type == GUMBO_NODE_TEXT) {
        QString text = QString::fromUtf8(node->v.text.text).trimmed();
        if (!text.isEmpty()) {
            texts.append(text);
        }
        return;
    } else if (node->type == GUMBO_NODE_ELEMENT || node->type == GUMBO_NODE_TEMPLATE) {
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            searchForText(static_cast<GumboNode*>(children->data[i]), texts);
        }
    }
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // Create main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("ULDictionary - 词典查询");
    mainWindow.resize(800, 600);
    
    // Create central widget
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    
    // Create top row with input field and search button
    QHBoxLayout* topLayout = new QHBoxLayout();
    
    QLineEdit* inputField = new QLineEdit(centralWidget);
    inputField->setPlaceholderText("请输入要查询的单词...");
    inputField->setMinimumHeight(35);
    inputField->setStyleSheet("font-size: 14px; padding: 5px;");
    
    QPushButton* searchButton = new QPushButton("查询", centralWidget);
    searchButton->setMinimumHeight(35);
    searchButton->setMinimumWidth(80);
    searchButton->setStyleSheet("font-size: 14px; font-weight: bold;");
    
    topLayout->addWidget(inputField);
    topLayout->addWidget(searchButton);
    
    mainLayout->addLayout(topLayout);
    
    // Create rich text display area
    QTextEdit* resultDisplay = new QTextEdit(centralWidget);
    resultDisplay->setReadOnly(true);
    resultDisplay->setStyleSheet("font-size: 13px; padding: 10px;");
    
    // Set initial welcome message with rich text formatting
    resultDisplay->setHtml(
        "<h2 style='color: #2c3e50;'>欢迎使用 ULDictionary</h2>"
        "<p style='color: #7f8c8d;'>请在上方输入框中输入要查询的单词，然后点击查询按钮。</p>"
        "<hr>"
        "<p><b>功能特点：</b></p>"
        "<ul>"
        "<li>C++20 标准</li>"
        "<li>Qt6 图形界面</li>"
        "<li>Gumbo HTML 解析器集成</li>"
        "<li>Cambridge Dictionary 在线查询</li>"
        "<li>跨平台支持 (Windows, Linux, macOS)</li>"
        "</ul>"
    );
    
    mainLayout->addWidget(resultDisplay);
    
    // Create network manager
    QNetworkAccessManager* networkManager = new QNetworkAccessManager(&mainWindow);
    
    // Connect search button to lambda function
    QObject::connect(searchButton, &QPushButton::clicked, [inputField, resultDisplay, networkManager]() {
        QString word = inputField->text().trimmed();
        
        if (word.isEmpty()) {
            resultDisplay->setHtml(
                "<p style='color: #e74c3c;'><b>错误：</b>请输入要查询的单词。</p>"
            );
            return;
        }
        
        // Display loading message
        resultDisplay->setHtml(
            "<h2 style='color: #2c3e50;'>正在查询：" + word + "</h2>"
            "<p style='color: #7f8c8d;'>正在从 Cambridge Dictionary 获取数据...</p>"
        );
        
        // Construct Cambridge Dictionary URL
        QString urlString = QString("https://dictionary.cambridge.org/dictionary/english-chinese-simplified/%1?q=Chinese").arg(word);
        QUrl url(urlString);
        
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36");
        
        // Send GET request
        QNetworkReply* reply = networkManager->get(request);
        
        // Handle response
        QObject::connect(reply, &QNetworkReply::finished, [reply, resultDisplay, word]() {
            if (reply->error() == QNetworkReply::NoError) {
                // Read response data
                QByteArray responseData = reply->readAll();
                QString htmlContent = QString::fromUtf8(responseData);
                
                // Parse HTML with Gumbo
                GumboOutput* output = gumbo_parse(responseData.constData());
                
                if (output) {
                    // Extract text content
                    QStringList texts;
                    searchForText(output->root, texts);
                    
                    // Clean up Gumbo parser
                    gumbo_destroy_output(&kGumboDefaultOptions, output);
                    
                    // Display the full HTML content
                    resultDisplay->setHtml(htmlContent);
                } else {
                    resultDisplay->setHtml(
                        "<p style='color: #e74c3c;'><b>错误：</b>无法解析 HTML 内容。</p>"
                    );
                }
            } else {
                // Display error message
                resultDisplay->setHtml(
                    QString("<h2 style='color: #e74c3c;'>查询失败</h2>"
                           "<p><b>错误：</b>%1</p>"
                           "<p><b>单词：</b>%2</p>"
                           "<p>请检查网络连接或稍后重试。</p>")
                    .arg(reply->errorString())
                    .arg(word)
                );
            }
            
            reply->deleteLater();
        });
    });
    
    // Allow Enter key to trigger search
    QObject::connect(inputField, &QLineEdit::returnPressed, searchButton, &QPushButton::click);
    
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    
    return app.exec();
}
