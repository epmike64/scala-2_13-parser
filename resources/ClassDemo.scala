
abstract class Storage[K, V](val namespace: String, val maxSize: Int) {

  def put(key: K, value: V): Boolean
  def get(key: K): Option[V]

  def isFull(currentSize: Int): Boolean = currentSize >= maxSize
  def qualifiedName(tag: String): String = s"$namespace::$tag"
}


class Repository[K, V](val name: String, private val capacity: Int)
    extends Storage[K, V](namespace = name, maxSize = capacity) {

  private var store: Map[K, V] = Map.empty
  private var accessCount: Int = 0
  val createdAt: Long          = System.currentTimeMillis()

  def put(key: K, value: V): Boolean = {
    if (isFull(store.size)) false
    else {
      store = store.updated(key, value)
      true
    }
  }

  def get(key: K): Option[V] = {
    accessCount += 1
    store.get(key)
  }

  def transform[W](f: V => W): Repository[K, W] = {
    val next = new Repository[K, W](name + "_transformed", capacity)
    store.foreach { case (k, v) => next.put(k, f(v)) }
    next
  }

  def stats: String =
    s"[${qualifiedName(name)}] entries=${store.size} capacity=$capacity accesses=$accessCount"
}

/*
val repo = new Repository[String, Int]("scores", capacity = 3)

repo.put("alice", 42)
repo.put("bob",   17)

println(repo.get("alice"))   // Some(42)
println(repo.isFull(3))      // true  — inherited from Storage
println(repo.stats)          // [scores::scores] entries=2 capacity=3 accesses=1*/