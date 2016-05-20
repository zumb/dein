<?hh //partial

namespace spec\Zumb\Dein;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Dein\Instantiator;
use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;

class ContainerServiceSpec extends ObjectBehavior
{
  public function let($instantiator, $method, $provider, $inspector)
  {
    $inspector->beADoubleOf(ClassInspector::class);
    $provider->beADoubleOf(Provider::class);
    $method->beADoubleOf(\ReflectionMethod::class);
    $instantiator->beADoubleOf(Instantiator::class);
    $this->beConstructedWith($instantiator);
  }

  public function it_returns_instance($instantiator, $inspector)
  {
    $instantiator->inspector(\stdClass::class)
      ->willReturn($inspector);
    $instantiator->make($inspector, $this)
      ->shouldBeCalled()
      ->willReturn("instance");
    $this->get(\stdClass::class)
      ->shouldReturn("instance");
  }

  public function it_adds_a_provider_instance($provider, $instantiator, $method, $inspector)
  {
    $method->getReturnTypeText()
      ->willReturn("SomeClass");
    $instantiator->method($provider, "get")
      ->willReturn($method);
    $this->addProvider($provider);
    $inspector->is("SomeClass")
      ->willReturn(true);
    $this->getProvider($inspector)
      ->shouldReturn($provider);
  }

}
