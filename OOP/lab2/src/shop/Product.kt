package shop

class Product(val name: String) {
    companion object {
        private var last_product_id: Int = 0
        private var products = mutableListOf<Product>()
    }
    private val id: Int = ++last_product_id

    init {
        products.add(this)
    }
}