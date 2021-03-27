package limits

import backup.Backup

interface Limit {
    fun check(backup: Backup): Boolean
}