# Лабораторная #3 по ООП на Котлине

### [Условие](https://reports.artrey.ru/task/14/)

## Использование

* Создайте экземпляр класса гонки `AirRace`, `GroundRace`, `GeneralRace`, передав в него расстояние трека гонки
    ```
    val race = GroundRace(5000F)
    ```
  
* Создайте экземпляр класса транспорта, например `Centaur` и `CrossCountryBoots`
    ```
    val centaur = Centaur()
    val boots = CrossCountryBoots()
    ```
  
* Добавьте их в гонку
    ```
    race.addVehicle(boots)
    race.addVehicle(centaur)
    ```
  
* Запустите гонку и определите победителя
    ```
    val winner = race.run()
    ```
