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
import translators.GoogleScriptAPI;
import translators.Languages;
import translators.Translator;

import java.io.IOException;

/**
 * Action to replace selected text with a choice of languages for translation.
 */

public class InputReplacing extends AnAction {

    @Override
    public void actionPerformed(@NotNull AnActionEvent event) {
        final Editor editor = event.getRequiredData(CommonDataKeys.EDITOR);
        final String selectedText = editor.getSelectionModel().getSelectedText();
        final Project project = event.getRequiredData(CommonDataKeys.PROJECT);
        final Document document = editor.getDocument();
        final Caret primaryCaret = editor.getCaretModel().getPrimaryCaret();

        if (selectedText != null) {
            TranslatorForms.showDialogWithTwoInputs(TranslatorForms.LANGUAGES_SELECTION).ifPresent(stringStringSimpleEntry ->
                    WriteCommandAction.runWriteCommandAction(project, () -> {
                        try {
                            final Translator translator = new GoogleScriptAPI();
                            document.replaceString(
                                    primaryCaret.getSelectionStart(), primaryCaret.getSelectionEnd(),
                                    translator.translate(
                                            Languages.valueOf(stringStringSimpleEntry.getKey()).getTitle(),
                                            Languages.valueOf(stringStringSimpleEntry.getValue()).getTitle(),
                                            selectedText
                                    )
                            );
                        } catch (IOException e) {
                            TranslatorForms.showTranslateErrorMessage();
                        }
                    })
            );
            primaryCaret.removeSelection();
        } else {
            TranslatorForms.showNoSelectedMessage();
        }
    }
}
