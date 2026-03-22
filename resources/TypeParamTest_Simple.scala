
/*class Box[A](val value: A) {
  def map[B](f: A => B): Box[B] = new Box(f(value))
  override def toString: String = s"Box($value)"
}*/

class TypeParamTest {
  def calculate[A: Numeric](x: A = 5 + 7, y: A = 6 * 8): A = {
    val num = implicitly[Numeric[A]]
    num.plus(x, y)
  }
}