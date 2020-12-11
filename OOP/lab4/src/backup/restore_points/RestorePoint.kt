package backup.restore_points

import system.File
import system.System

abstract class RestorePoint(private val files: MutableList<File>) {
    private val id: Int = kotlin.random.Random(1337).nextInt()

    val createDate: Int = System.currentTime

    val size: Int = files.sumBy { it.size }

    fun contains(file: File): Boolean {
        for (savedFile in files) {
            if (file.filename == savedFile.filename && file.path == savedFile.path) {
                return true
            }
        }
        return false
    }

    override fun toString(): String {
        return "createDate: $createDate\nsize: $size\ncontent: ${files.joinToString { "[$it]" }}"
    }
}