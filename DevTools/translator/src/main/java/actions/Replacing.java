package actions;

import com.intellij.openapi.actionSystem.AnAction;
import com.intellij.openapi.actionSystem.AnActionEvent;
import com.intellij.openapi.actionSystem.CommonDataKeys;
import com.intellij.openapi.command.WriteCommandAction;
import com.intellij.openapi.editor.Caret;
import com.intellij.openapi.editor.Document;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.project.Project;
import forms.TranslatorForms;
import org.jetbrains.annotations.NotNull;
import properties.AppSettingsState;
import translators.GoogleScriptAPI;
import translators.Languages;

import java.io.IOException;

//Replacing

public class Replacing extends AnAction {

    @Override
    public void actionPerformed(@NotNull AnActionEvent event) {
        final Editor editor = event.getRequiredData(CommonDataKeys.EDITOR);
        final String selectedText = editor.getSelectionModel().getSelectedText();
        final Project project = event.getRequiredData(CommonDataKeys.PROJECT);
        final Document document = editor.getDocument();
        final Caret primaryCaret = editor.getCaretModel().getPrimaryCaret();

        if (selectedText != null) {
            WriteCommandAction.runWriteCommandAction(project, () -> {
                try {
                    document.replaceString(
                            primaryCaret.getSelectionStart(), primaryCaret.getSelectionEnd(),
                            new GoogleScriptAPI().translate(
                                    Languages.valueOf(AppSettingsState.getInstance().languageFrom).getTitle(),
                                    Languages.valueOf(AppSettingsState.getInstance().languageTo).getTitle(),
                                    selectedText
                            )
                    );
                } catch (IOException e) {
                    TranslatorForms.showTranslateErrorMessage();
                }
            });
            primaryCaret.removeSelection();
        } else {
            TranslatorForms.showNoSelectedMessage();
        }
    }
}
