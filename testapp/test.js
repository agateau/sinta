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

var mainWindow = waitForActiveWindow();
console.log("mainWindow=" + mainWindow);
tools.screenshot(mainWindow, "mainwindow.png");

var popupButton = tools.findChild(mainWindow, "openPopupButton");
var fontComboBox = tools.findChild(mainWindow, "fontComboBox");

for (idx = 0; idx < 10; ++idx) {
    fontComboBox.setCurrentIndex(idx);
    var fontName = fontComboBox.currentText;
    console.log(fontName);

    popupButton.click();
    var popup = waitForActiveWindow(mainWindow);
    tools.screenshot(popup, fontName + ".png");
    popup.close();
}

mainWindow.close();
