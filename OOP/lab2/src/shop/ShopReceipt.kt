package shop

class ShopReceipt {
    class ReceiptItem(val product: Product, val count: Int, val price: Float? = null)

    private val receipt = mutableListOf<ReceiptItem>()

    constructor() {

    }
    constructor(map: Map<Product, Int>) {
        for ((product, count) in map) {
            push(product, count)
        }
    }

    fun push(product: Product, count: Int, price: Float? = null) {
        receipt.add(ReceiptItem(product, count, price))
    }

    fun getReceiptSize(): Int {
        return receipt.size
    }

    fun getReceipt(): MutableList<ReceiptItem> {
        return receipt
    }

    fun getConsignmentAsString(): String {
        var answer = ""
        for (receiptItem in receipt) {
            answer += "Product ${receiptItem.product.name} - Count ${receiptItem.count} - Price ${receiptItem.price}\n"
        }
        return answer
    }

    fun getReceiptAsString(): String {
        var answer = ""
        for (receiptItem in receipt) {
            answer += "Product ${receiptItem.product.name} - Count ${receiptItem.count}\n"
        }
        return answer
    }
}