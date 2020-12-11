package system

class File(val path: String, val filename: String) {
    var data: String = ""
        set(data: String) {
            field = data
            lastModified = System.currentTime
            size = data.length
        }

    var lastModified: Int = System.currentTime
        private set

    var size: Int = 0
        private set

    fun clone(into: String): File {
        val clone = File(into, filename)
        clone.data = data
        return clone
    }

    override fun toString(): String {
        return data
    }
}
