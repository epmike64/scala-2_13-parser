
class Box[A](val value: A) {
  def map[B](f: A => B): Box[B] = new Box(f(value))
  override def toString: String = s"Box($value)"
}