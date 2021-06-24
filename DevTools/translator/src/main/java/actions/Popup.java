package actions;

import com.intellij.openapi.actionSystem.AnAction;
import com.intellij.openapi.actionSystem.AnActionEvent;
import com.intellij.openapi.actionSystem.CommonDataKeys;
import com.intellij.openapi.command.WriteCommandAction;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.ui.popup.Balloon;
import com.intellij.openapi.ui.popup.JBPopupFactory;
import com.intellij.ui.JBColor;
import com.intellij.ui.awt.RelativePoint;
import forms.TranslatorForms;
import org.jetbrains.annotations.NotNull;
import properties.AppSettingsState;
import translators.GoogleScriptAPI;
import translators.Languages;
import translators.Translator;

import java.io.IOException;

/**
 * Action to show the translation in a pop-up with default languages.
 */

public class Popup extends AnAction {

    @Override
    public void actionPerformed(@NotNull AnActionEvent event) {
        final Editor editor = event.getRequiredData(CommonDataKeys.EDITOR);
        final String selectedText = editor.getSelectionModel().getSelectedText();
        final Project project = event.getRequiredData(CommonDataKeys.PROJECT);

        if (selectedText != null) {
            WriteCommandAction.runWriteCommandAction(project, () -> {
                try {
                    Translator translator = new GoogleScriptAPI();
                    final String result = translator.translate(
                            Languages.valueOf(AppSettingsState.getInstance().languageFrom).getTitle(),
                            Languages.valueOf(AppSettingsState.getInstance().languageTo).getTitle(),
                            selectedText
                    );
                    final RelativePoint relPoint = JBPopupFactory.getInstance()
                            .guessBestPopupLocation(editor.getSelectionModel().getEditor());
                    JBPopupFactory.getInstance().createHtmlTextBalloonBuilder(
                            result, null, JBColor.LIGHT_GRAY, null
                    )
                            .createBalloon()
                            .show(relPoint, Balloon.Position.below);
                } catch (IOException e) {
                    TranslatorForms.showTranslateErrorMessage();
                }
            });
        } else {
            TranslatorForms.showNoSelectedMessage();
        }
    }
}