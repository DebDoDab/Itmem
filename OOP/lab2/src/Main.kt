import shop.Product
import shop.ShopReceipt
import shop.Store
import kotlin.random.Random

fun generateShopList(products: MutableList<Product>, random: Random): ShopReceipt {
    val shopList = ShopReceipt()
    val product1 = products.random()
    val amount1 = random.nextInt(1, 4)
    shopList.push(product1, amount1)
    val product2 = products.random()
    val amount2 = random.nextInt(1, 4)
    shopList.push(product2, amount2)
    return shopList
}

fun main(args: Array<String>) {
    val random = Random(228)
    val stores = mutableListOf<Store>()
    stores.add(Store("Pyaterochka", "41, Kronverskaya st."))
    stores.add(Store("VkussVill", "Petroga"))
    stores.add(Store("Ashan", "za Mkadom"))

    val products = mutableListOf<Product>()
    products.add(Product("white monster energy"))
    products.add(Product("Lidskiy kvass"))
    products.add(Product("cactus"))
    products.add(Product("pig fat"))
    products.add(Product("White-Red-White flag"))
    products.add(Product("bear"))
    products.add(Product("beer"))
    products.add(Product("pillow"))
    products.add(Product("borgar"))
    products.add(Product("fried chicken"))

    for (i in 0..15) {
        val store = stores.random()
        val consignment = ShopReceipt()
        for (j in 0..2) {
            val product = products.random()
            val productAmount = random.nextInt(1, 10)
            val productPrice = random.nextFloat() * 228
            consignment.push(product, productAmount, productPrice)
        }
        store.deliverSupply(consignment)
        println("We delivered \n${consignment.getConsignmentAsString()}in ${store.name}\n")
    }
    println("")

    for (product in products) {
        val store = Store.findCheapestProduct(product)
        if (store == null) {
            println("There is no ${product.name} in any shop")
        } else {
            println("Cheapest ${product.name} is in ${store.name}")
        }
    }
    println("\n")

    for (store in stores) {
        val moneyAmount = random.nextFloat() * 1000
        val receipt = store.analysePrice(moneyAmount)
        println("In ${store.name} on $moneyAmount we can buy \n${receipt.getReceiptAsString()}")
    }
    println("")

    for (store in stores) {
        val shopList = generateShopList(products, random)

        val cost = store.buy(shopList)
        if (cost == null) {
            println("We cannot buy \n${shopList.getReceiptAsString()}in ${store.name}\n")
        } else {
            println("To buy \n${shopList.getReceiptAsString()}in ${store.name} you have to spend $cost\n")
        }
    }
    println("\n")


    for (i in 1..5) {
        val shopList = generateShopList(products, random)

        val store = Store.findCheapestProducts(shopList)

        if (store == null) {
            println("We cannot buy\n${shopList.getReceiptAsString()}in any shop\n")
        } else {
            println("The shop with lowest price on\n${shopList.getReceiptAsString()}is ${store.name}\n")
        }
    }

}