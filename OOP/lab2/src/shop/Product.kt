package shop

class Product(val name: String) {
    companion object {
        var last_product_id: Int = 0
        var products = mutableListOf<Product>()
    }
    private val id: Int = ++last_product_id

    init {
        products.add(this)
    }
}