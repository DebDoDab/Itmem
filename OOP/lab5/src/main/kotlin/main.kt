import accounts.DepositFunction
import banks.Bank
import transactions.Transaction
import java.lang.NullPointerException

fun main(args: Array<String>) {
    val depositLimits = mutableListOf<Pair<Float, Float>>(Pair(10F, 0.1F), Pair(50F, 0.15F), Pair(1000F, 0.25F))
    val depositFunction = DepositFunction(depositLimits)
    val bank = Bank(depositFunction)

    bank.doubtfulLimit = 50F
    bank.creditLimit = 10F
    bank.creditCommission = 1F
    bank.debitDailyBonusPercentage = 0.01F
    bank.depositTerm = 100

    val builder = bank.getClientBuilder()
    builder.setName("Vaditel", "Ruinkin")
    builder.setAddress("Kolotuskina, Pushkina st.")
    builder.setPassportData("228")
    val vaditel = bank.createClient(builder)
    val vaditelAccount = bank.addClientDebitAccount(vaditel)
    vaditelAccount.addMoney(100F)

    builder.reset()
    builder.setName("Roberto", "from Germany")
    builder.setAddress("Korobki na Kupchino")

    val roberto = bank.createClient(builder)
    val robertoAccount = bank.addClientCreditAccount(roberto)
    robertoAccount.addMoney(10F)

    builder.reset()
    builder.setName("Pojiloi", "Pilot")
    builder.setAddress("Eve online")
    builder.setPassportData("1337")

    val tutor = bank.createClient(builder)
    val tutorAccount = bank.addClientDeposit(tutor)
    tutorAccount.addMoney(50F)

    println("After init")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    System.day = 31
    bank.applyDate()

    println("After month")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    val transaction1 = bank.makeTransaction(robertoAccount, vaditelAccount, 20F)

    println("After transaction")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()


    System.day = 61
    bank.applyDate()

    println("After 2nd month")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    bank.cancelTransaction(transaction1)

    println("After canceling transaction")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    val transaction2 = bank.makeTransaction(tutorAccount, robertoAccount, 20F)

    println("After deposit transaction")
    println(transaction2.status)
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    System.day = 110
    bank.applyDate()

    println("After 100 days")
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    val transaction3 = bank.makeTransaction(tutorAccount, robertoAccount, 20F)

    println("After deposit transaction")
    println(transaction3.status)
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()

    val transaction4 = bank.makeTransaction(robertoAccount, vaditelAccount, 20F)

    println("After credit transaction")
    println(transaction4.status)
    println(vaditelAccount.balance)
    println(robertoAccount.balance)
    println(tutorAccount.balance)
    println()


}