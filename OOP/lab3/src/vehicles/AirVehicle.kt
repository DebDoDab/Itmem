package vehicles

abstract class AirVehicle: Vehicle {
    abstract fun distanceReduce(distance: Float): Float

    override fun run(distance: Float): Float {
        return distance * (1 - distanceReduce(distance)) / speed;
    }
}
