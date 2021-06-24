package forms;

import com.intellij.openapi.ui.ComboBox;
import com.intellij.openapi.ui.Messages;
import translators.Languages;

import javax.swing.*;
import java.util.AbstractMap;
import java.util.Objects;
import java.util.Optional;

public class TranslatorForms {

    public static final String DEFAULT_TITLE = "Translator";
    public static final String LANGUAGES_SELECTION = "Select default languages";
    public static final String SETTING_DEFAULT_LANGUAGES = "Select languages";

    public static Optional<AbstractMap.SimpleEntry<String, String>> showDialogWithTwoInputs(String title) {
        final String[] languages = Languages.names();
        final ComboBox<String> from = new ComboBox<>(languages);
        final ComboBox<String> to = new ComboBox<>(languages);
        final JPanel myPanel = new JPanel();

        myPanel.add(new JLabel("from:"));
        myPanel.add(from);
        myPanel.add(Box.createHorizontalStrut(15));
        myPanel.add(new JLabel("to:"));
        myPanel.add(to);

        if (JOptionPane.showConfirmDialog(null, myPanel,
                title, JOptionPane.OK_CANCEL_OPTION) == JOptionPane.OK_OPTION) {
            final String langFrom = Objects.requireNonNull(from.getSelectedItem()).toString();
            final String langTo = Objects.requireNonNull(to.getSelectedItem()).toString();
            return Optional.of(new AbstractMap.SimpleEntry<>(langFrom, langTo));
        } else {
            return Optional.empty();
        }
    }

    public static void showNoSelectedMessage() {
        Messages.showMessageDialog("Please select a text for translation.",
                DEFAULT_TITLE, Messages.getWarningIcon());
    }

    public static void showTranslateErrorMessage() {
        Messages.showMessageDialog("Failed to translate.",
                DEFAULT_TITLE, Messages.getErrorIcon());
    }
}


