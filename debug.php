<?php
declare(strict_types=1);
function a(int $a) : void {
    write("A");
    function b() : void {
        write("B");
    }
}
