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

  public function it_returns_instance_without_provider_and_constructor($class, $container)
  {
    $class->getConstructor()
      ->willReturn(null);
    $class->newInstance()
      ->shouldBeCalled()
      ->willReturn("object");
    $this->make($class, $container)
      ->shouldReturn("object");
  }

  public function it_returns_instance_from_provider($class, $container, $provider)
  {
    $object = new \stdClass();
    $class->getConstructor()
      ->willReturn(null);
    $container->getProvider($class)
      ->willReturn($provider);
    $provider->get($class)
      ->willReturn($object);
    $this->make($class, $container)
      ->shouldReturn($object);
  }

  public function it_resolves_constructor_parameters_with_container($class, $container, $constructor)
  {
    $constructor->getParameters()
      ->willReturn(["param"]);
    $class->getConstructor()
      ->willReturn($constructor);
    $class->newInstanceArgs(["param" => "value"])
      ->willReturn("object");
    $container->getProvider($class)
      ->willReturn(null);
    $container->resolve($constructor)
      ->willReturn(["param" => "value"])
      ->shouldBeCalled();
    $this->make($class, $container)
      ->shouldReturn("object");
  }
}
