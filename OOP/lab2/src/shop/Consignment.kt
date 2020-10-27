package shop

class Consignment {
    class ConsignmentItem(val product: Product, val count: Int, val price: Float) {}

    val consignment = mutableListOf<ConsignmentItem>()
}