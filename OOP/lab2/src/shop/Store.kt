package shop

import java.util.*
import shop.Product
import kotlin.math.floor

class Store(val name: String, val address: String) {
    val id: Int = ++last_shop_id

    class ProductStock {
        var count: Int = 0
        var price: Float = 0F
    }

    var products = mutableMapOf<Product, ProductStock>()

    companion object {
        var last_shop_id: Int = 0

        var shops = mutableListOf<Store>()

        fun findCheapestProduct(product: Product): Store? {
            var storeWithLowestPrice: Store? = null
            var leastProductPrice: Float = 0F
            for (shop in shops) {
                val price = shop.getProductPrice(product)
                if (price != null && (storeWithLowestPrice == null || price < leastProductPrice)) {
                    storeWithLowestPrice = shop
                    leastProductPrice = price
                }
            }
            return storeWithLowestPrice
        }
        fun findCheapestProducts(receipt: ShopReceipt): Store? {
            var storeWithLowestPrice: Store? = null
            var lowestCost: Float = 0F
            for (shop in shops) {
                val cost = shop.buy(receipt)
                if (cost != null &&(storeWithLowestPrice == null || lowestCost > cost)) {
                    storeWithLowestPrice = shop
                    lowestCost = cost
                }
            }
            return storeWithLowestPrice
        }
    }

    init {
        shops.add(this)
    }

    fun getProductPrice(product: Product): Float? {
        if (products.containsKey(product)) {
            return products[product]!!.price
        }
        else {
            return null
        }
    }

    fun deliverProduct(product: Product, count: Int, price: Float) {
        if (!products.containsKey(product)) {
            products[product] = ProductStock()
        }
        products[product]!!.count += count
        products[product]!!.price = price
    }

    fun deliverSupply(consignment: ShopReceipt) {
        for (consignmentItem in consignment.getReceipt()) {
            val product = consignmentItem.product
            val count = consignmentItem.count
            val price = consignmentItem.price ?: throw NoPriceException("You have to initialise price value")
            deliverProduct(product, count, price)
        }
    }

    fun analysePrice(moneyAmount: Float): ShopReceipt {
        val analysis = ShopReceipt()
        for ((product, stock) in products) {
            analysis.push(product, floor(moneyAmount / stock.price).toInt())
        }
        return analysis
    }

    fun buy(shopList: ShopReceipt): Float? {
        var cost: Float = 0F
        for (receiptItem in shopList.getReceipt()) {
            val product = receiptItem.product
            val count = receiptItem.count
            if (!products.containsKey(product) || products[product]!!.count < count) {
                return null
            }
            cost += products[product]!!.price * count
        }
        return cost
    }


}