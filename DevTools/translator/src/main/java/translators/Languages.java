package translators;

import java.util.Arrays;

public enum Languages {
    English ("en"),
    German ("de"),
    Russian ("ru"),
    French ("fr"),
    Korean ("ko"),
    Chinese ("zh"),
    Czech ("cs"),
    Italian ("it"),
    Japanese ("ja"),
    Arabic ("ar"),
    Afrikaans ("af"),
    Bengali ("bn"),
    Bulgarian ("bg"),
    Danish ("da"),
    Finnish ("fi"),
    Georgian ("ka"),
    Greek ("el"),
    Hindi ("hi"),
    Indonesian ("id"),
    Irish ("ga"),
    Kazakh ("kk"),
    Latin ("la"),
    Macedonian ("mk"),
    Mongolian ("mn"),
    Norwegian ("no"),
    Polish ("pl"),
    Portuguese ("pt"),
    Romanian ("ro"),
    Serbian ("sr"),
    Slovak ("sk"),
    Swedish ("sv"),
    Thai ("th"),
    Turkish ("tr"),
    Vietnamese ("vi");

    private final String title;

    Languages(String title) {
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public static String[] names() {
        return Arrays.toString(Languages.values())
                .replaceAll("^.|.$", "")
                .split(", ");
    }
}
