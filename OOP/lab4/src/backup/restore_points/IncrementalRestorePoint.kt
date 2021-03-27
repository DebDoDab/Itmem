package backup.restore_points

import system.File

class IncrementalRestorePoint(files: MutableList<File>): RestorePoint(files) {
}