package vehicles

abstract class GroundVehicle : Vehicle {
    abstract val restInterval: Float

    abstract fun restDuration(iteration: Int): Float

    override fun run(distance: Float): Float {
        var time = distance / speed
        val restCount = (time / restInterval).toInt()

        (1..restCount).forEach { time += restDuration(it) }
        return time
    }
}
