function waitFor(fcn) {
    while (true) {
        var result = fcn();
        if (result) {
            return result;
        }
        tools.processEvents();
    }
}

function waitForActiveWindow(excluded) {
    return waitFor(function() {
        var window = tools.activeWindow();
        if (window === null || window === excluded) {
            return null;
        }
        return window;
    });
}

// Wait for the main window to be visible
var mainWindow = waitForActiveWindow();
console.log("mainWindow=" + mainWindow);

// Take a screenshot of it
tools.screenshot(mainWindow, "mainwindow.png");

// Find the UI elements we need. The names are the QObject name.
var popupButton = tools.findChild(mainWindow, "openPopupButton");
var fontComboBox = tools.findChild(mainWindow, "fontComboBox");

// Loop on fonts, open the popup and take a screenshot of it
for (idx = 0; idx < 10; ++idx) {
    fontComboBox.setCurrentIndex(idx);
    var fontName = fontComboBox.currentText;
    console.log(fontName);

    popupButton.click();
    var popup = waitForActiveWindow(mainWindow);
    tools.screenshot(popup, fontName + ".png");
    popup.close();
}

// Close the app
mainWindow.close();
