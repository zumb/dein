<?hh //partial

namespace spec\Dein\Providers;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Dein\ContainerService;
use Dein\Reflection\ClassInspector;

class ContainerServiceProviderSpec extends ObjectBehavior
{
  public function let($container, $class)
  {
    $container->beADoubleOf(ContainerService::class);
    $class->beADoubleOf(ClassInspector::class);
  }

  public function it_returns_always_the_same_container($container, $class)
  {
    $this->beConstructedWith($container);
    $this->get($class)
      ->shouldReturn($container);
  }
}