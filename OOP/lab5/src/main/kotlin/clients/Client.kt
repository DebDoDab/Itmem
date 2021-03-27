package clients

import accounts.Account
import banks.Bank

class Client(val bank: Bank, val first_name: String, val secondName: String, var address: String?, var passportData: String?) {
    companion object {
        private var lastUsedId = 0

        private fun getNewId(): Int {
            return lastUsedId++
        }
    }
    val id: Int = getNewId()

    val accountsIds = mutableListOf<Int>()

    fun isDoubtful(): Boolean {
        return address == null || passportData == null
    }
}