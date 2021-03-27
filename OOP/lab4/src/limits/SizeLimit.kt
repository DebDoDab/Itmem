package limits

import backup.Backup

class SizeLimit(var size: Int): Limit {
    override fun check(backup: Backup): Boolean {
        return backup.size <= size
    }
}