import org.junit.jupiter.api.Test;
import translators.GoogleScriptAPI;

import java.io.IOException;
import java.nio.charset.StandardCharsets;

import static org.junit.jupiter.api.Assertions.assertEquals;


public class APITests {
    @Test
    void fromEnglishTranslateTests() throws IOException {
        assertEquals(new String("Привет всем".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "ru", "Hello everyone"));
        assertEquals(new String("Hallo zusammen".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "de", "Hello everyone"));
        assertEquals(new String("Bonjour à tous".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "fr", "Hello everyone"));
        assertEquals(new String("大家好".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "zh", "Hello everyone"));
        assertEquals(new String("Ahoj všichni".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "cs", "Hello everyone"));
        assertEquals(new String("Ciao a tutti".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "it", "Hello everyone"));
        assertEquals(new String("みなさん、こんにちは".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("en", "ja", "Hello everyone"));
    }
    @Test
    void fromFrenchTranslateTests() throws IOException {
        assertEquals(new String("Привет".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "ru", "bonjour"));
        assertEquals(new String("Hallo".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "de", "bonjour"));
        assertEquals(new String("Hello".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "en", "bonjour"));
        assertEquals(new String("你好".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "zh", "bonjour"));
        assertEquals(new String("Ahoj".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "cs", "bonjour"));
        assertEquals(new String("Buongiorno".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "it", "bonjour"));
        assertEquals(new String("こんにちは".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("fr", "ja", "bonjour"));
    }
    @Test
    void fromGermanTranslateTests() throws IOException {
        assertEquals(new String("дети".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "ru", "kinder"));
        assertEquals(new String("enfants".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "fr", "kinder"));
        assertEquals(new String("children".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "en", "kinder"));
        assertEquals(new String("孩子们".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "zh", "kinder"));
        assertEquals(new String("děti".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "cs", "kinder"));
        assertEquals(new String("bambini".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "it", "kinder"));
        assertEquals(new String("子供達".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("de", "ja", "kinder"));
    }
    @Test
    void fromRussianTranslateTests() throws IOException {
        assertEquals(new String("vor einem Monat".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "de", "месяц назад"));
        assertEquals(new String("il y a un mois".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "fr", "месяц назад"));
        assertEquals(new String("month ago".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "en", "месяц назад"));
        assertEquals(new String("一个月前".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "zh", "месяц назад"));
        assertEquals(new String("před měsícem".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "cs", "месяц назад"));
        assertEquals(new String("un mese fa".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "it", "месяц назад"));
        assertEquals(new String("ひと月前".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("ru", "ja", "месяц назад"));
    }
    @Test
    void fromChineseTranslateTests() throws IOException {
        assertEquals(new String("Mein Name ist Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "de", "我叫亚历克斯"));
        assertEquals(new String("Mon nom est Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "fr", "我叫亚历克斯"));
        assertEquals(new String("My name is alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "en", "我叫亚历克斯"));
        assertEquals(new String("Меня зовут Алекс".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "ru", "我叫亚历克斯"));
        assertEquals(new String("Moje jméno je Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "cs", "我叫亚历克斯"));
        assertEquals(new String("Mi chiamo Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "it", "我叫亚历克斯"));
        assertEquals(new String("私の名前はアレックスです".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("zh", "ja", "我叫亚历克斯"));
    }
    @Test
    void fromCzechTranslateTests() throws IOException {
        assertEquals(new String("Mein Name ist Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "de", "Moje jméno je Alex"));
        assertEquals(new String("Mon nom est Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "fr", "Moje jméno je Alex"));
        assertEquals(new String("My name is Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "en", "Moje jméno je Alex"));
        assertEquals(new String("Меня зовут Алекс".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "ru", "Moje jméno je Alex"));
        assertEquals(new String("我的名字叫亚历克斯".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "zh", "Moje jméno je Alex"));
        assertEquals(new String("Mi chiamo Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "it", "Moje jméno je Alex"));
        assertEquals(new String("私の名前はアレックスです".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("cs", "ja", "Moje jméno je Alex"));
    }
    @Test
    void fromItalianoTranslateTests() throws IOException {
        assertEquals(new String("Ich heiße Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "de", "Mi chiamo Alex"));
        assertEquals(new String("Je m'appelle Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "fr", "Mi chiamo Alex"));
        assertEquals(new String("My name's Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "en", "Mi chiamo Alex"));
        assertEquals(new String("Меня зовут алекс".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "ru", "Mi chiamo Alex"));
        assertEquals(new String("Jmenuji se Alex".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "cs", "Mi chiamo Alex"));
        assertEquals(new String("我叫亚历克斯".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "zh", "Mi chiamo Alex"));
        assertEquals(new String("私の名前はアレックスです".getBytes(), StandardCharsets.UTF_8), new GoogleScriptAPI().translate("it", "ja", "Mi chiamo Alex"));

    }
}
