<?hh //strict
namespace Zumb\Dein\Interfaces;

use Zumb\Dein\Reflection\ClassInspector;

interface Provider<Tp>
{
  public function get(ClassInspector<Tp> $class):Tp;
}
