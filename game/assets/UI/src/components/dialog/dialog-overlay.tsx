"use client";
import { Overlay } from "@radix-ui/react-dialog";
import { tw } from "@/tw";
import { ComponentPropsWithoutRef, ElementRef, forwardRef } from "react";

export const DialogOverlay = forwardRef<ElementRef<typeof Overlay>, ComponentPropsWithoutRef<typeof Overlay>>(
  ({ className, ...props }, ref) => (
    <Overlay
      className={tw(
        "fixed inset-0 z-50 bg-black/80  data-[state=open]:animate-in data-[state=closed]:animate-out data-[state=closed]:fade-out-0 data-[state=open]:fade-in-0",
        className,
      )}
      ref={ref}
      {...props}
    />
  ),
);
DialogOverlay.displayName = Overlay.displayName;
