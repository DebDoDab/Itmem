# Лабораторная #1 по ООП на Котлине

### [Условие](https://reports.artrey.ru/task/7/)

## Использование

* Создайте экземпляр класса `INIParser`
    ```
    val parser = INIParser()
    ```
* Вызовите метод `.parse`
    ```
    val data = parser.data(File(filename))
    ```
* Получите значение определенного типа с именем `property` из секции `section`\
    ```
    data.tryGetInt(section, property)
    data.tryGetString(section, property)
    data.tryGetDouble(section, property)
    data.tryGet<Int>(section, property)
    data.tryGet<String>(section, property)
    data.tryGet<Double>(section, property)
    ```


