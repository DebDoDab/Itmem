package backup

import backup.restore_points.FullRestorePoint
import backup.restore_points.IncrementalRestorePoint
import backup.restore_points.RestorePoint
import exceptions.CannotCreateIncrementalRestorePointException
import exceptions.EmptyBackupException
import limits.Limit
import system.File
import kotlin.random.Random

class Backup {
    private val id: Int = Random(228).nextInt()

    private val restorePoints = mutableListOf<RestorePoint>()

    private val trackingFiles = mutableListOf<File>()

    private val limits = mutableListOf<Limit>()

    private var deleteAtAllLimits: Boolean = false

    var size: Int = 0
        private set

    fun getFirstRestorePointCreationDate(): Int? {
        if (restorePoints.isEmpty()) {
            return null
        }
        return restorePoints.first().createDate
    }

    fun getRestorePointCount(): Int {
        return restorePoints.size
    }

    fun addFileToTrack(file: File) {
        if (trackingFiles.contains(file)) {
            return
        }
        trackingFiles.add(file)
    }

    fun deleteFileFromTracking(file: File) {
        trackingFiles.remove(file)
    }

    fun createRestorePoint(incremental: Boolean = false): RestorePoint {
        if (restorePoints.isEmpty() && incremental) {
            throw CannotCreateIncrementalRestorePointException(
                    "There is no full restore point to add incremental restore point"
            )
        }

        if (incremental) {
            createIncrementalRestorePoint()
        } else {
            createFullRestorePoint()
        }
        size += restorePoints.last().size

        useLimits()
        return restorePoints.last()
    }

    private fun createFullRestorePoint() {
        val filesInNewRestorePoint = mutableListOf<File>()

        for (file in trackingFiles) {
            filesInNewRestorePoint.add(file.clone("/backup$id/restorePoint${restorePoints.size}"))
        }
        restorePoints.add(FullRestorePoint(filesInNewRestorePoint))
    }

    private fun createIncrementalRestorePoint() {
        val filesInNewRestorePoint = mutableListOf<File>()

        for (file in trackingFiles) {
            val lastRestorePointWithFile = findLastRestorePointWithFile(file)
            if (lastRestorePointWithFile.createDate < file.lastModified) {
                filesInNewRestorePoint.add(file.clone("/backup$id/restorePoint${restorePoints.size}"))
            }
        }

        restorePoints.add(IncrementalRestorePoint(filesInNewRestorePoint))
    }

    private fun findLastRestorePointWithFile(file: File): RestorePoint {
        for (restorePoint in restorePoints.asReversed()) {
            if (restorePoint.contains(file)) {
                return restorePoint
            }
        }
        return restorePoints.first()
    }

    fun changeLimits(limits: MutableList<Limit>, deleteAtAllLimits: Boolean) {
        this.limits.clear()
        limits.forEach { this.limits.add(it) }
        this.deleteAtAllLimits = deleteAtAllLimits

        useLimits()
    }

    private fun useLimits() {
        while (!checkLimits()) {
            deleteFirstRestorePoint()
        }
    }

    private fun checkLimits(): Boolean {
        for (limit in limits) {
            if (deleteAtAllLimits && limit.check(this)) return true
            if (!deleteAtAllLimits && !limit.check(this)) return false
        }
        return !deleteAtAllLimits
    }

    private fun deleteFirstRestorePoint() {
        if (restorePoints.isEmpty()) {
            throw EmptyBackupException("Nothing to delete")
        }

        size -= restorePoints.first().size
        restorePoints.removeAt(0)
        while (restorePoints.isNotEmpty() && restorePoints.first() is IncrementalRestorePoint) {
            size -= restorePoints.first().size
            restorePoints.removeAt(0)
        }
    }

    override fun toString(): String {
        return "BACKUP $id\n${restorePoints.joinToString { "$it\n" }}"
    }
}