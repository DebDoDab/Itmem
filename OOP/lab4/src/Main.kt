import backup.Backup
import limits.RestorePointCountLimit
import system.File
import system.System

fun case0() {
    println("\n\nCASE 0")
    System.currentTime = 123
    val file1 = File("/home/vadim/case0", "foo.txt")
    file1.data = "asd"
    val file2 = File("/home/vadim/case0", "bar.txt")
    file2.data = "qwerty"

    val backup = Backup()
    backup.addFileToTrack(file1)
    backup.addFileToTrack(file2)

    System.currentTime = 234
    val fullRestorePoint = backup.createRestorePoint(incremental=false)
    println(fullRestorePoint.toString())
    println()

    System.currentTime = 345
    file2.data = "qwe"

    System.currentTime = 456
    val incrementalRestorePoint1 = backup.createRestorePoint(incremental=true)
    println(incrementalRestorePoint1.toString())
    println()

    System.currentTime = 567
    backup.deleteFileFromTracking(file1)
    file1.data = "asdd"
    file2.data = "qwertyuiop"

    System.currentTime = 678
    val incrementalRestorePoint2 = backup.createRestorePoint(incremental=true)
    println(incrementalRestorePoint2.toString())
    println()
}

fun case1() {
    println("\n\nCASE 1")
    System.currentTime = 1000
    val file1 = File("/home/vadim/case1", "foo.txt")
    file1.data = "asd"
    val file2 = File("/home/vadim/case1", "bar.txt")
    file2.data = "qwerty"

    val backup = Backup()
    backup.addFileToTrack(file1)
    backup.addFileToTrack(file2)

    System.currentTime = 1234
    val fullRestorePoint = backup.createRestorePoint(incremental=false)
    println(fullRestorePoint.toString())
    println()

    System.currentTime = 1345
    file2.data = "qwe"

    System.currentTime = 1456
    val incrementalRestorePoint1 = backup.createRestorePoint(incremental=false)
    println(incrementalRestorePoint1.toString())
    println()

    val limit = RestorePointCountLimit(1)
    backup.changeLimits(mutableListOf(limit), deleteAtAllLimits=true)

    println(backup)
}

fun main(args: Array<String>) {

    case0()
    case1()


}