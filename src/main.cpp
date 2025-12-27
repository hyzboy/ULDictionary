#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QString>
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
        "<li>跨平台支持 (Windows, Linux, macOS)</li>"
        "</ul>"
    );
    
    mainLayout->addWidget(resultDisplay);
    
    // Connect search button to lambda function
    QObject::connect(searchButton, &QPushButton::clicked, [inputField, resultDisplay]() {
        QString word = inputField->text().trimmed();
        
        if (word.isEmpty()) {
            resultDisplay->setHtml(
                "<p style='color: #e74c3c;'><b>错误：</b>请输入要查询的单词。</p>"
            );
            return;
        }
        
        // Display search results with rich text formatting
        QString html = QString(
            "<h2 style='color: #2c3e50;'>查询结果：%1</h2>"
            "<hr>"
            "<p><b style='color: #3498db;'>单词：</b><span style='font-size: 18px;'>%2</span></p>"
            "<p><b style='color: #3498db;'>发音：</b>[示例发音]</p>"
            "<p><b style='color: #3498db;'>词性：</b>n. / v. / adj.</p>"
            "<hr>"
            "<h3 style='color: #16a085;'>释义：</h3>"
            "<ol>"
            "<li><b>名词：</b>示例释义 1</li>"
            "<li><b>动词：</b>示例释义 2</li>"
            "<li><b>形容词：</b>示例释义 3</li>"
            "</ol>"
            "<hr>"
            "<h3 style='color: #16a085;'>例句：</h3>"
            "<p style='margin-left: 20px;'><i>\"This is an example sentence.\"</i></p>"
            "<p style='margin-left: 20px; color: #7f8c8d;'>这是一个例句。</p>"
            "<hr>"
            "<p style='color: #95a5a6; font-size: 11px;'>提示：这是演示数据，实际使用时需要连接词典数据源。</p>"
        ).arg(word).arg(word);
        
        resultDisplay->setHtml(html);
    });
    
    // Allow Enter key to trigger search
    QObject::connect(inputField, &QLineEdit::returnPressed, searchButton, &QPushButton::click);
    
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    
    return app.exec();
}
