package vehicles

interface Vehicle {
    val speed: Float

    fun run(distance: Float): Float
}
