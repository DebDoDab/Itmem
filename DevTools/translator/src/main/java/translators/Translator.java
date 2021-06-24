package translators;

import java.io.IOException;

public interface Translator {

    String translate(String langFrom, String langTo, String text) throws IOException;

}
