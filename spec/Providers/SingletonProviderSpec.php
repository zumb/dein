<?hh //partial

namespace spec\Zumb\Dein\Providers;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Dein\ContainerService;
use Zumb\Dein\Reflection\ClassInspector;

class SingletonProviderSpec extends ObjectBehavior
{
  public function let($class)
  {
    $class->beADoubleOf(ClassInspector::class);
  }

  public function it_returns_always_the_same_object($class)
  {
    $object = new \stdClass();
    $this->beConstructedWith($object);
    $this->get($class)
      ->shouldReturn($object);
    $this->get($class)
      ->shouldReturn($object);
  }
}
