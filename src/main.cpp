#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
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
    mainWindow.setWindowTitle("ULDictionary - Qt6 C++20 with Gumbo Parser");
    mainWindow.resize(800, 600);
    
    // Create central widget
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    
    // Add labels with information
    QLabel* titleLabel = new QLabel("ULDictionary - Qt6 C++20 with Gumbo HTML Parser", centralWidget);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
    layout->addWidget(titleLabel);
    
    QLabel* cppVersionLabel = new QLabel(
        QString("Compiled with C++%1").arg(__cplusplus), 
        centralWidget
    );
    layout->addWidget(cppVersionLabel);
    
    // Platform information
    QString platform;
#ifdef PLATFORM_WINDOWS
    platform = "Windows";
#elif defined(PLATFORM_MACOS)
    platform = "macOS";
#elif defined(PLATFORM_LINUX)
    platform = "Linux";
#else
    platform = "Unknown";
#endif
    
    QLabel* platformLabel = new QLabel(QString("Platform: %1").arg(platform), centralWidget);
    layout->addWidget(platformLabel);
    
    QLabel* qtVersionLabel = new QLabel(QString("Qt Version: %1").arg(QT_VERSION_STR), centralWidget);
    layout->addWidget(qtVersionLabel);
    
    QLabel* gumboLabel = new QLabel("Gumbo HTML Parser: Integrated", centralWidget);
    layout->addWidget(gumboLabel);
    
    // Gumbo parser demo section
    QLabel* demoLabel = new QLabel("Gumbo HTML Parser Demo:", centralWidget);
    demoLabel->setStyleSheet("font-weight: bold; margin-top: 10px;");
    layout->addWidget(demoLabel);
    
    // Demo: Parse a simple HTML string
    const char* html = "<html><body><h1>Hello World</h1><p>This is a test paragraph.</p></body></html>";
    GumboOutput* output = gumbo_parse(html);
    
    QString parsedResult;
    if (output) {
        // Extract text from parsed HTML
        QStringList extractedTexts;
        searchForText(output->root, extractedTexts);
        
        parsedResult = "Parsed HTML text: " + extractedTexts.join(", ");
        
        // Clean up Gumbo parser
        gumbo_destroy_output(&kGumboDefaultOptions, output);
    } else {
        parsedResult = "Error: Failed to parse HTML";
    }
    
    QLabel* resultLabel = new QLabel(parsedResult, centralWidget);
    resultLabel->setWordWrap(true);
    layout->addWidget(resultLabel);
    
    layout->addStretch();
    
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    
    return app.exec();
}
