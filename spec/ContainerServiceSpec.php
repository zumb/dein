<?hh //partial

namespace spec\Zumb\Dein;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Dein\Instantiator;
use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;
use Zumb\Dein\Resolver;
use Zumb\Dein\ProvidersPool;

class ContainerServiceSpec extends ObjectBehavior
{
  public function let($instantiator, $method, $provider, $inspector, $resolver, $providers)
  {
    $inspector->beADoubleOf(ClassInspector::class);
    $provider->beADoubleOf(Provider::class);
    $method->beADoubleOf(\ReflectionMethod::class);
    $instantiator->beADoubleOf(Instantiator::class);
    $resolver->beADoubleOf(Resolver::class);
    $providers->beADoubleOf(ProvidersPool::class);
    $this->beConstructedWith($instantiator, $resolver, $providers);
  }



  public function it_returns_instance_without_provider_and_constructor($inspector, $instantiator)
  {
    $instantiator->inspector("SomeClass")
      ->willReturn($inspector);
    $inspector->getConstructor()
      ->willReturn(null);
    $inspector->newInstance()
      ->shouldBeCalled()
      ->willReturn("object");
    $this->get("SomeClass")
      ->shouldReturn("object");
  }

  public function it_returns_instance_from_provider($inspector, $instantiator, $provider, $method, $providers, $resolver)
  {
    $object = new \stdClass();
    $instantiator->inspector("SomeClass")
      ->willReturn($inspector);
    $instantiator->method($provider, "get")
      ->willReturn($method);
    $inspector->getConstructor()
      ->willReturn(null);
    $providers->get($inspector)
      ->willReturn($provider);
    $resolver->attributes($method, $this)
      ->willReturn([]);
    $method->invokeArgs($provider, [$inspector])
      ->willReturn($object);
    $this->get("SomeClass")
      ->shouldReturn($object);
  }

}
