package banks

import accounts.Account
import clients.Client
import System
import accounts.CreditAccount
import accounts.DebitAccount
import clients.ClientBuilder

class Bank {
    companion object {
        private var lastUsedId = 0

        private fun getNewId(): Int {
            return lastUsedId++
        }
    }

    val id: Int = getNewId()
    private val accounts = mutableListOf<Account>()
    private val clients = mutableListOf<Client>()

    var doubtfulLimit: Float = 100F
    var debitDailyBonusPercentage: Float = 0.01F
    var creditLimit: Float = 100F
    var creditCommission: Float = 1F

    private var lastBonusDay: Int = 0

    fun applyDate() {
        while (lastBonusDay < System.day) {
            for (account in accounts) {
                account.dailyBonus()
                account.dailyCommission()
                if (lastBonusDay % 30 == 0) {
                    account.monthlyBonus()
                }
            }
            lastBonusDay += 1
        }
    }

    fun getClientBuilder(): ClientBuilder {
        return ClientBuilder(this)
    }

    fun createClient(clientBuilder: ClientBuilder): Client {
        val client = clientBuilder.getClient()
        clientBuilder.reset()

        clients.add(client)
        return client
    }

    fun deleteClient(client_id: Int): Boolean {
        for (client in clients) {
            if (client.id == client_id) {
                clients.remove(client)
                return true
            }
        }
        return false
    }

    fun addClientAccount(client: Client, accountType: String): Account {
        if (accountType == "debit") {
            return addClientDebitAccount(client)
        } else if (accountType == "credit") {
            return addClientCreditAccount(client)
        }
        throw NullPointerException()
    }

    fun addClientCreditAccount(client: Client): CreditAccount {
        val account = CreditAccount(client, creditLimit, creditCommission)
        accounts.add(account)
        client.accountsIds.add(account.id)
        return account
    }

    fun addClientDebitAccount(client: Client): DebitAccount {
        val account = DebitAccount(client, debitDailyBonusPercentage)
        accounts.add(account)
        client.accountsIds.add(account.id)
        return account
    }

    fun deleteClientAccount() {

    }
}