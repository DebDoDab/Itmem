package properties;

import com.intellij.openapi.options.Configurable;
import org.jetbrains.annotations.Nls;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;

public class AppSettingsConfigurable implements Configurable {

    private AppSettingsComponent mySettingsComponent;

    @Nls(capitalization = Nls.Capitalization.Title)
    @Override
    public String getDisplayName() {
        return "Settings";
    }

    @Nullable
    @Override
    public JComponent createComponent() {
        mySettingsComponent = new AppSettingsComponent();
        return mySettingsComponent.getPanel();
    }

    @Override
    public boolean isModified() {
        AppSettingsState settings = AppSettingsState.getInstance();
        boolean modified = !mySettingsComponent.getLanguageFromText().equals(settings.languageFrom);
        modified |= !mySettingsComponent.getLanguageToText().equals(settings.languageTo);
        return modified;
    }

    @Override
    public void apply() {
        AppSettingsState settings = AppSettingsState.getInstance();
        settings.languageFrom = mySettingsComponent.getLanguageFromText();
        settings.languageTo = mySettingsComponent.getLanguageToText();
    }

    @Override
    public void reset() {
        AppSettingsState settings = AppSettingsState.getInstance();
        mySettingsComponent.setLanguageFromText(settings.languageFrom);
        mySettingsComponent.setLanguageToText(settings.languageTo);
    }

    @Override
    public void disposeUIResources() {
        mySettingsComponent = null;
    }
}
