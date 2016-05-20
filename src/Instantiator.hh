<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\ContainerService;
use Zumb\Dein\Reflection\ClassInspector;

class Instantiator
{
  public function make(ClassInspector<mixed> $class, ContainerService $container):mixed
  {
    $constructor = $class->getConstructor();
    $provider = $container->getProvider($class);
    if($provider != null) {
      // UNSAFE
      return $provider->get($class);
    } elseif($constructor != null) {
      if(count($constructor->getParameters())) {
        return $class->newInstanceArgs(
          $container->resolve($constructor)
        );
      }
    }
    return $class->newInstance();
  }

  public function method(mixed $class, string $name):\ReflectionMethod
  {
    return new \ReflectionMethod($class, $name);
  }

  public function inspector(mixed $class):ClassInspector<mixed>
  {
    return new ClassInspector($class);
  }
}
