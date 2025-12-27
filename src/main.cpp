#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    
    // Create main window
    QMainWindow mainWindow;
    mainWindow.setWindowTitle("ULDictionary - Qt6 C++20 Application");
    mainWindow.resize(600, 400);
    
    // Create central widget
    QWidget* centralWidget = new QWidget(&mainWindow);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    
    // Add labels with information
    QLabel* titleLabel = new QLabel("ULDictionary - Cross-platform Qt6 C++20 Application", centralWidget);
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
    
    // Arguments
    QLabel* argsLabel = new QLabel(QString("Arguments: %1").arg(argc), centralWidget);
    layout->addWidget(argsLabel);
    
    for (int i = 0; i < argc; ++i) {
        QLabel* argLabel = new QLabel(QString("  [%1]: %2").arg(i).arg(argv[i]), centralWidget);
        layout->addWidget(argLabel);
    }
    
    layout->addStretch();
    
    mainWindow.setCentralWidget(centralWidget);
    mainWindow.show();
    
    return app.exec();
}
