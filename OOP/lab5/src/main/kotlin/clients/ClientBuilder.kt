package clients

import banks.Bank

class ClientBuilder(val bank: Bank) {
    var firstName: String? = null
    var secondName: String? = null
    var address: String? = null
    var passportData: String? = null

    fun setName(firstName: String, secondName: String): Boolean {
        this.firstName = firstName
        this.secondName = secondName
        return true
    }

    fun setAddress(address: String): Boolean {
        this.address = address
        return true
    }

    fun setPassportData(passportData: String): Boolean {
        this.passportData = passportData
        return true
    }

    fun reset(): Boolean {
        firstName = null
        secondName = null
        address = null
        passportData = null
        return true
    }

    fun getClient(): Client {
        return Client(bank, firstName!!, secondName!!, address, passportData)
    }
}