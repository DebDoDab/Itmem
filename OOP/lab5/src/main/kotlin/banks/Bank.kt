package banks

import clients.Client
import System
import accounts.*
import clients.ClientBuilder
import transactions.Transaction

class Bank(var depositFunction: DepositFunction) {
    companion object {
        private var lastUsedId = 0

        private fun getNewId(): Int {
            return lastUsedId++
        }
    }

    val id: Int = getNewId()
    private val accounts = mutableListOf<Account>()
    private val clients = mutableListOf<Client>()
    private val transactions = mutableListOf<Transaction>()

    var doubtfulLimit: Float = 100F
    var debitDailyBonusPercentage: Float = 0.01F
    var creditLimit: Float = 100F
    var creditCommission: Float = 1F
    var depositTerm: Int = 120

    private var lastBonusDay: Int = 0

    fun applyDate() {
        while (lastBonusDay < System.day) {
            for (account in accounts) {
                if (account.lastBonusDay >= lastBonusDay) {
                    break
                }
                account.lastBonusDay++
                account.dailyBonus()
                account.dailyCommission()
                if (lastBonusDay % 30 == 0) {
                    account.monthlyBonus()
                }
            }
            lastBonusDay += 1
        }
    }

    fun getTransaction(transactionId: Int): Transaction {
        for (transaction in transactions) {
            if (transaction.id == transactionId) {
                return transaction
            }
        }
        throw NullPointerException("Not found")
    }

    fun getClient(clientId: Int): Client {
        for (client in clients) {
            if (client.id == clientId) {
                return client
            }
        }
        throw NullPointerException("Not found")
    }

    fun getAccount(accountId: Int): Account {
        for (account in accounts) {
            if (account.id == accountId) {
                return account
            }
        }
        throw NullPointerException("Not found")
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

    fun deleteClient(clientId: Int): Boolean {
        for (client in clients) {
            if (client.id == clientId) {
                clients.remove(client)
                return true
            }
        }
        return false
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

    fun addClientDeposit(client: Client): Deposit {
        val account = Deposit(client, depositFunction, depositTerm)
        accounts.add(account)
        client.accountsIds.add(account.id)
        return account
    }

    fun deleteClientAccount(accountId: Int): Boolean {
        for (account in accounts) {
            if (account.id == accountId) {
                accounts.remove(account)
                return true
            }
        }
        return false
    }

    fun makeTransaction(source: Account, destination: Account, amountOfMoney: Float): Transaction {
        val transaction = Transaction(source, destination, amountOfMoney)
        transactions.add(transaction)
        source.transactionsIds.add(transaction.id)
        destination.transactionsIds.add(transaction.id)
        transaction.proceed()
        return transaction
    }

    fun cancelTransaction(transaction: Transaction): Boolean {
        for (transaction_ in transactions) {
            if (transaction.id == transaction_.id) {
                transactions.remove(transaction_)
                break
            }
        }
        return transaction.cancel()
    }
}