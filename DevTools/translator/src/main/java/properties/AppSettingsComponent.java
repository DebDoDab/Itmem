package properties;

import com.intellij.openapi.ui.ComboBox;
import com.intellij.ui.components.JBLabel;
import com.intellij.util.ui.FormBuilder;
import org.jetbrains.annotations.NotNull;
import translators.Languages;

import javax.swing.*;

public class AppSettingsComponent {

    private final JPanel myMainPanel;
    private final ComboBox<String> languageFrom = new ComboBox<>(Languages.names());
    private final ComboBox<String> languageTo = new ComboBox<>(Languages.names());

    public AppSettingsComponent() {
        myMainPanel = FormBuilder.createFormBuilder()
                .addComponent(new JBLabel("Default language settings:"))
                .addLabeledComponent(new JBLabel("Language from: "),
                        languageFrom, 1, false)
                .addLabeledComponent(new JBLabel("Language to: "),
                        languageTo, 1, false)
                .addComponentFillVertically(new JPanel(), 0)
                .getPanel();
    }

    public JPanel getPanel() {
        return myMainPanel;
    }

    public JComponent getLanguageFrom() {
        return languageFrom;
    }

    public JComponent getLanguageTo() {
        return languageTo;
    }

    @NotNull
    public String getLanguageFromText() {
        return languageFrom.getItem();
    }

    @NotNull
    public String getLanguageToText() {
        return languageTo.getItem();
    }

    public void setLanguageFromText(@NotNull String newText) {
        languageFrom.setItem(newText);
    }

    public void setLanguageToText(@NotNull String newText) {
        languageTo.setItem(newText);
    }
}

