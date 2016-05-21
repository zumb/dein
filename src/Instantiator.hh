<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\ContainerService;
use Zumb\Dein\Reflection\ClassInspector;

class Instantiator
{
  public function method(mixed $class, string $name):\ReflectionMethod
  {
    return new \ReflectionMethod($class, $name);
  }

  public function inspector(mixed $class):ClassInspector<mixed>
  {
    if(is_string($class)) {
      $type = [];
      preg_match('/^([^<]+)/', $class, $type);
      $class = $type[1];
    }
    return new ClassInspector($class);
  }
}
