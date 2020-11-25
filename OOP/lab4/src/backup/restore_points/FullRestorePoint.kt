package backup.restore_points

import system.File

class FullRestorePoint(files: MutableList<File>): RestorePoint(files) {
}