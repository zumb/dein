<?hh //strict
namespace Dein\Interfaces;

use Dein\Reflection\ClassInspector;

interface Provider<Tp>
{
  public function get(ClassInspector<Tp> $class):Tp;
}
