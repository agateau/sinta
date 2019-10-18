function runScript(mainWindow) {
    // Wait for the main window to be visible
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
        var popup = tools.waitForActiveWindow(mainWindow);
        tools.screenshot(popup, fontName + ".png");
        popup.close();
    }

    // Close the app
    mainWindow.close();
}

tools.waitForActiveWindowAsync(runScript);
