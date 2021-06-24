package actions;

import com.intellij.openapi.actionSystem.AnAction;
import com.intellij.openapi.actionSystem.AnActionEvent;
import com.intellij.openapi.actionSystem.CommonDataKeys;
import com.intellij.openapi.command.WriteCommandAction;
import com.intellij.openapi.project.Project;
import forms.TranslatorForms;
import org.jetbrains.annotations.NotNull;
import properties.AppSettingsState;

/**
 * Action to select default languages for translation.
 * Default languages can be changed using this action or in the plugin settings (File -> Settings -> Tools -> Translator).
 */

public class DefaultLanguages extends AnAction {

    @Override
    public void actionPerformed(@NotNull AnActionEvent event) {
        final Project project = event.getRequiredData(CommonDataKeys.PROJECT);
        TranslatorForms.showDialogWithTwoInputs(TranslatorForms.SETTING_DEFAULT_LANGUAGES).ifPresent(stringStringSimpleEntry ->
                WriteCommandAction.runWriteCommandAction(project, () -> {
                    final AppSettingsState settings = AppSettingsState.getInstance();
                    settings.languageFrom = stringStringSimpleEntry.getKey();
                    settings.languageTo = stringStringSimpleEntry.getValue();
                })
        );
    }
}