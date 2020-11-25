# Лабораторная #4 по ООП на Котлине

### [Условие](https://reports.artrey.ru/task/15/)

## Использование

* Создайте файл
    ```
    System.currentTime = 123
    val file = File("/home/foo", "bar.txt")
    ```
  
* Создайте бекап и добавьте в него файл
    ```
    val backup = Backup()
    backup.addFileToTrack(file)
    ```
  
* Создайте полную точку восстановления и выведите ее контент в консоль
    ```
    System.currentTime = 234
    val fullRestorePoint = backup.createRestorePoint(incremental=false)
    ```
  
* Измените файл и создайте инкрементальную точку восстановления и выведите ее контент в консоль
    ```
    System.currentTime = 345
    file2.data = "qwe"

    System.currentTime = 456
    val incrementalRestorePoint1 = backup.createRestorePoint(incremental=true)
    println(incrementalRestorePoint1.toString())
    ```
  
* Создайте лимит и примените его
    ```
    val limit = RestorePointCountLimit(1)
    backup.changeLimits(mutableListOf(limit), deleteAtAllLimits=true)
    ```

* Убедитесь, что в бекапе не осталось точек восстановления
    ```
    println(backup)
    ```
  
* Убедитесь, что нельзя создать новую инкрементальную точку восстановления
    ```
    System.currentTime = 567
    val incrementalRestorePoint2 = backup.createRestorePoint(incremental=true)
    ```
