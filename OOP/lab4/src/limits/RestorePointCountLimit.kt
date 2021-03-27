package limits

import backup.Backup

class RestorePointCountLimit(val count: Int): Limit {
    override fun check(backup: Backup): Boolean {
        return backup.getRestorePointCount() <= count
    }
}