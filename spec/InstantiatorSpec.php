<?hh //partial

namespace spec\Zumb\Dein;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Dein\ContainerService;
use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;

class InstantiatorSpec extends ObjectBehavior
{
  public function let($class, $container, $provider, $constructor)
  {
    $class->beADoubleOf(ClassInspector::class);
    $container->beADoubleOf(ContainerService::class);
    $provider->beADoubleOf(Provider::class);
    $constructor->beADoubleOf(\ReflectionMethod::class);
  }

  
}
