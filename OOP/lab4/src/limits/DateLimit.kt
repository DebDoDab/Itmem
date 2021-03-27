package limits

import backup.Backup

class DateLimit(val date: Int): Limit {
    override fun check(backup: Backup): Boolean {
        return backup.getFirstRestorePointCreationDate() == null || backup.getFirstRestorePointCreationDate()!! <= date
    }
}